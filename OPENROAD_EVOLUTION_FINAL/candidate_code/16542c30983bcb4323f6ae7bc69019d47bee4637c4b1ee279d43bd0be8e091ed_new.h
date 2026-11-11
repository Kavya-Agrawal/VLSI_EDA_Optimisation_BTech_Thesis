// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.29728509;
  double density_weight = 0.59586734;
  double prefix_weight = 0.17229035;
  double neighborhood_weight = 0.04325668;
  double late_weight = 0.29863751;
  double critical_weight = 0.02518314;
  unsigned budget = 31;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
