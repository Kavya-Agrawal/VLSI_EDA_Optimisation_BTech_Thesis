// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.17294987;
  double density_weight = 0.14418640;
  double prefix_weight = 0.22896483;
  double neighborhood_weight = 0.16423890;
  double late_weight = 0.29423671;
  double critical_weight = 0.30225861;
  unsigned budget = 33;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
