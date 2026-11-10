// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50449356;
  double density_weight = 0.13058035;
  double prefix_weight = 0.23635671;
  double neighborhood_weight = 0.39702377;
  double late_weight = 0.23491329;
  double critical_weight = 0.06283551;
  unsigned budget = 39;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
