// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09091800;
  double density_weight = 0.06961126;
  double prefix_weight = 0.31476204;
  double neighborhood_weight = 0.15430700;
  double late_weight = 0.28025123;
  double critical_weight = 0.02524087;
  unsigned budget = 13;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
